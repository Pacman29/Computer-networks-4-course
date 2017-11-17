fun main(args : Array<String>) {

    var messages = Messages();
    var sortMessages = sorter(messages.getMessages(),"развитие")

    val sender = Sender("email","password");

    for(message in sortMessages)
        sender.send("TEST",message,"toEmail","fromEmail");
}
