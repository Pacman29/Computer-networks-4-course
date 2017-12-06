
import java.io.*
import java.net.Socket


class Client(val socket: Socket,
             val uid: String,
             val db: DataBase) {
    fun process() {
        val input = DataInputStream(socket.getInputStream())
        var output = DataOutputStream(socket.getOutputStream())

        try {
            while (true){
                var req = input.readUTF()
                println("client $uid send: $req \n")

            }
        } catch (e : IOException){
            println(e.message)
            println("client $uid ERROR: CONNECTION CLOSE \n")
            db.returnUID(uid)
            socket.close()
        }
    }
}