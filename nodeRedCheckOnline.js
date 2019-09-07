var message = null;


// activate markdown
//msg.payload.options = {disable_web_page_preview : true, parse_mode : "Markdown"};
//return msg;
var caldaia = context.get('caldaia')||false;
var enemon = context.get('enemon')||false;
var chrono = context.get('chrono')||false;
//CALDAIA
if(msg.topic=="192.168.1.199")
{
    if((msg.payload === false) && (caldaia!==false))
    {
        context.set('caldaia',false);
        //send msg caldaia offiline
        message = "caldaia OFF" ;
    }
    else if ((msg.payload !== false) && (caldaia===false))
    {
        context.set('caldaia',msg.payload);
        //send msg caldaia online
        message = "caldaia ON" ;
    }
}
//ENEMON
else if(msg.topic=="192.168.1.217")
{
    if((msg.payload === false) && (enemon!==false))
    {
        context.set('enemon',false);
        //send msg enemon offiline
        message = "enemon OFF" ;
    }
    else if ((msg.payload !== false) && (enemon===false))
    {
        context.set('enemon',msg.payload);
        //send msg caldaia online
        message = "enemon ON" ;
    }
}
//CHRONO
else if(msg.topic=="192.168.1.215")
{
    if((msg.payload === false) && (chrono!==false))
    {
        context.set('chrono',false);
        //send msg chrono offiline
        message = "chrono OFF" ;
    }
    else if ((msg.payload !== false) && (chrono===false))
    {
        context.set('chrono',msg.payload);
        //send msg caldaia online
        message = "chrono ON" ;
    }
}
if(message!=null) 
{
    msg1.payload = {chatId : -378129953, type : 'message', content : message};
    return msg1;
}
return null;