import java.io.DataInputStream
import java.io.DataOutputStream
import java.io.IOException
import java.net.Socket
import java.util.*

fun main(args: Array<String>) {
    var socket = Socket("0.0.0.0",8000)

    var input = DataInputStream(socket.getInputStream())
    var output = DataOutputStream(socket.getOutputStream())
    var strAccess = input.readUTF()
    if(strAccess.contains("500")){
        println(strAccess)
        socket.close()
        return
    } else {
        println(strAccess)
    }
    try {
        while(socket.isConnected){
            print("Input request : ")
            var keyInput = Scanner(System.`in`)
            output.writeUTF(keyInput.nextLine())
            println("Request send")

        }
    } catch (e: IOException){
        println("CLIENT ERROR: ${e.message}")
    }
}