/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */ 
/** USBX Component                                                        */ 
/**                                                                       */
/**   IP3516 Controller Driver                                            */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/* Include necessary system files.  */

#define UX_SOURCE_CODE

#include "ux_api.h"
#include "ux_hcd_ip3516.h"
#include "ux_host_stack.h"


/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _ux_hcd_ip3516_power_root_hubs                      PORTABLE C      */
/*                                                           6.1          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This function powers individually or in gang mode the root HUBs     */ 
/*    attached to the IP3516 controller.                                  */
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_ip3516                            Pointer to IP3516 controller  */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    None                                                                */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _ux_hcd_ip3516_register_read          Read IP3516 register          */ 
/*    _ux_hcd_ip3516_register_write         Write IP3516 register         */ 
/*    _ux_utility_delay_ms                  Delay                         */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    IP3516 Controller Driver                                            */
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  xx-xx-xxxx     Chaoqiong Xiao           Initial Version 6.1           */
/*                                                                        */
/**************************************************************************/
VOID  _ux_hcd_ip3516_power_root_hubs(UX_HCD_IP3516 *hcd_ip3516)
{

ULONG       ip3516_register;
UINT        port_index;


    /* Read the control PPC field. If the PPC field is set, the controller has 
       implemented port power.  */
    ip3516_register =  _ux_hcd_ip3516_register_read(hcd_ip3516, IP3516_HCCR_HCS_PARAMS);

    if (ip3516_register & IP3516_HC_RH_PPC)
    {

        /* We have power management in this controller. Apply power to each port.  */
        for (port_index = 0; port_index < hcd_ip3516 -> ux_hcd_ip3516_nb_root_hubs; port_index++)
        {
            
            /* Read register first to preserve existing settings.  */
            ip3516_register = _ux_hcd_ip3516_register_read(hcd_ip3516, IP3516_HCOR_PORT_SC + port_index);

            /* Apply power to a port.  */
            _ux_hcd_ip3516_register_write(hcd_ip3516, IP3516_HCOR_PORT_SC + port_index, ip3516_register | IP3516_HC_PS_PP);
        }
    }        

    /* The IP3516 needs some time for the power to be stable.  */
    _ux_utility_delay_ms(IP3516_HC_RH_POWER_STABLE_DELAY);

    /* Return to caller.  */
    return;
}    

