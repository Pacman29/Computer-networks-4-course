import java.lang.management.ManagementFactory
import java.text.SimpleDateFormat
import java.util.*

fun main(args: Array<String>) {
    var port = 8000
    var user_limit = 1
    var timeOut = 20

    for (i in args.indices) {
        if ("-p" == args[i]) {
            port = args[i + 1].toInt()
            continue
        }
        if ("-l" == args[i]) {
            user_limit = args[i + 1].toInt()
        }
    }
    Server(port, user_limit,timeOut).start()
}