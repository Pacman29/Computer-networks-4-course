

import java.net.PasswordAuthentication
import java.util.Properties

import javax.*
import javax.mail.*
import javax.mail.internet.InternetAddress
import javax.mail.internet.MimeMessage

class Sender(private val username: String, private val password: String) {
    private val props: Properties

    init {

        props = Properties()
        props.put("mail.smtp.auth", "true")
        props.put("mail.smtp.starttls.enable", "true")
        props.put("mail.smtp.host", "smtp.gmail.com")
        props.put("mail.smtp.port", "587")
    }

    fun send(subject: String, text: String, fromEmail: String, toEmail: String)
    {
        val session = Session.getInstance(props, object : Authenticator() {
            override fun getPasswordAuthentication(): javax.mail.PasswordAuthentication {
                return javax.mail.PasswordAuthentication(username,password)
            }
        })

        try {
            val message = MimeMessage(session)
            //от кого
            message.setFrom(InternetAddress(username))
            //кому
            message.setRecipients(Message.RecipientType.TO, InternetAddress.parse(toEmail))
            //Заголовок письма
            message.setSubject(subject)
            //Содержимое
            message.setText(text)

            //Отправляем сообщение
            Transport.send(message)
        } catch (e: MessagingException) {
            throw RuntimeException(e)
        }

    }
}