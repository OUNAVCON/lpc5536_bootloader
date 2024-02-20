(window["webpackJsonp"]=window["webpackJsonp"]||[]).push([["chunk-2d2183f0"],{c9bf:function(n,t,o){"use strict";o.r(t),o.d(t,"PcmObject",(function(){return a}));var e=o("53ca"),c=o("d4ec"),i=o("bee2"),r=o("ade3"),a=(o("d3b7"),function(){function n(){var t=this;Object(c["a"])(this,n),Object(r["a"])(this,"onSocketConnected",(function(){t.connected=!0,console.log("Connected to freeMASTER"),t.pcm.EnableEvents(!0)})),Object(r["a"])(this,"onSocketClose",(function(){t.connected=!1,console.warn("Socket closed")})),Object(r["a"])(this,"onSocketError",(function(n){t.connected=!1,console.error("Socket error: ",n.message)})),Object(r["a"])(this,"onServerError",(function(n){t.connected=!1,console.error("Server error: ",n.message)})),this.pcm,this.connected="",this.rpcs_addr="localhost:41000"}return Object(i["a"])(n,[{key:"startPcm",value:function(){"object"!==Object(e["a"])(this.pcm)?("undefined"!==typeof FreeMASTER?this.rpcs_addr=FreeMASTER.rpcs_addr:console.log("freeMaster is undefined, loading the default port..."),this.pcm=new PCM(this.rpcs_addr,this.onSocketConnected,this.onSocketClose,this.onSocketError),this.pcm.OnServerError=this.onServerError,this.pcm.OnSocketError=this.onSocketError):console.log("Already connected to freeMASTER")}},{key:"waitUntil",value:function(n,t){var o=this;n<10?(n+=1,this.connected?t():(console.log("Not connected yet, let's wait..."),setTimeout((function(){o.waitUntil(n,t)}),500))):console.error("Unable to connect to freeMASTER after 10 times")}},{key:"isCommPortOpen",value:function(n){var t=this;this.waitUntil(0,(function(){t.pcm.IsCommPortOpen().then((function(t){return n(t)})).catch((function(n){return console.log("Error: ",n)}))}))}},{key:"writeOutputFileContents",value:function(n,t){var o=this;this.waitUntil(0,(function(){o.pcm.LocalFileOpen(n,"w").then((function(e){var c=e.data;o.pcm.LocalFileWriteString(c,t,!1).then((function(t){console.log("Wrote "+t.data+" characters to "+n),o.pcm.LocalFileClose(c).then((function(){return console.log("Closed: "+n)})).catch((function(t){return console.log("Error: "+t+" while closing: "+n)}))})).catch((function(n){console.error(n)}))})).catch((function(n){console.error(n)}))}))}},{key:"readOutputFileContents",value:function(n,t){var o=this;this.waitUntil(0,(function(){o.pcm.LocalFileOpen(n,"r").then((function(e){var c=e.data;console.log("Opened "+n),o.pcm.LocalFileReadString(c,2147483647,!1).then((function(e){o.pcm.LocalFileClose(c).then((function(){console.log("Closed: "+n),t(e.data)})).catch((function(t){console.log("Error while closing: "+n+", error: "+t)}))})).catch((function(n){console.error(n)}))})).catch((function(n){console.log(n)}))}))}},{key:"checkIfFileExists",value:function(n){var t=this;return new Promise((function(o,e){t.waitUntil(0,(function(){t.pcm.LocalFileOpen(n,"r").then((function(e){o(n),t.pcm.LocalFileClose(e.data).then((function(){})).catch((function(){console.error("Error while closing file: "+n)}))})).catch((function(){e()}))}))}))}},{key:"checkVariable",value:function(n){var t=this;return new Promise((function(o,e){t.waitUntil(0,(function(){t.pcm.IsCommPortOpen().then((function(c){c.data?t.pcm.ReadVariable(n).then((function(n){o(n.data)})).catch((function(n){e(n)})):e("Cannot read variable - communication port is not open")}))}))}))}},{key:"writeVariable",value:function(n,t){var o=this;this.waitUntil(0,(function(){o.pcm.IsCommPortOpen().then((function(e){e.data?o.pcm.WriteVariable(n,t).then((function(){console.log("Variable",n,"was updated with value:",t)})).catch((function(n){console.log(n.msg)})):console.warn("Cannot write variable to freeMaster - communication port is not open.")}))}))}},{key:"readVariable",value:function(n,t){var o=this;this.waitUntil(0,(function(){o.pcm.IsCommPortOpen().then((function(e){e.data?o.pcm.ReadVariable(n).then((function(n){t(n.xtra)})).catch((function(o){console.log("Cannot find value: ",n,", error message is: ",o.msg),t("")})):(console.warn("Cannot read variable - communication port is not open."),t(""))}))}))}},{key:"subscribeVariable",value:function(n,t){var o=this;this.pcm.OnVariableChanged=function(n,o,e){t(n,e)},this.waitUntil(0,(function(){o.pcm.IsCommPortOpen().then((function(t){t.data?o.pcm.SubscribeVariable(n).then((function(){})).catch((function(n){console.log("Error: ",n)})):console.warn("Cannot subscribe variable - communication port is not open")}))}))}},{key:"onCommPortStateChanged",value:function(n){this.pcm.OnCommPortStateChanged=function(t){console.log("Port state changed:",t),n(t)}}}]),n}())}}]);
//# sourceMappingURL=chunk.js.map