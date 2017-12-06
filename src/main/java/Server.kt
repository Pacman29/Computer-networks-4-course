import javafx.application.Application.launch
import kotlinx.coroutines.experimental.CommonPool
import kotlinx.coroutines.experimental.launch
import java.io.DataOutputStream
import java.io.IOException
import java.net.ServerSocket
import java.util.concurrent.ExecutorService
import java.util.concurrent.Executors


class Server(val port: Int,
             val uLimit: Int,
             val timeOut: Int = 5) {
    fun start() {
        val socket = ServerSocket(port)
        println("Server started on port $port")
        val db = DataBase(uLimit);
        while (true) {
            val accept = socket.accept()
            accept.soTimeout = timeOut * 1000
            accept.keepAlive = true
            val out = DataOutputStream(accept.getOutputStream())
            val uid = db.getUID()
            if(uid == null){
                println("ERROR: NEW CLIENT NOT ADDED, CONNECTION CLOSE")
                out.writeUTF("500 SERVER ERROR: limit connection")
                accept.close()
                continue
            }
            out.writeUTF("200 You have access")
            println("NEW CLIENT ADDED uid: $uid")
            launch(CommonPool) {
                Client(accept,uid,db).process()
            }
        }
    }
}
