var message = null;
if(msg.payload.topic=="Terrazza")
{
    context.set('extT',msg.payload.Temp);
}
else if(msg.payload.topic=="DHTCamera")
{
    context.set('intT',msg.payload.Temp);
}
var fc = context.get('fuoriCaldo')||null;
var extT = context.get('extT')||false;
var intT = context.get('intT')||false;
if((extT > intT) && (fc!==true))
    {
        context.set('extT',msg.payload.Temp);
        context.set('fc',true);
        message = "Fuori fa più Caldo!" ;
    }
if((extT < intT) && (fc!==false))
{
    context.set('extT',msg.payload.Temp);
    context.set('fc',false);
    message = "Fuori fa più Freddo!" ;
}
if(message!=null) 
{
    msg.payload = {chatId : -378129953, type : 'message', content : message};
    return msg;
}
return null;