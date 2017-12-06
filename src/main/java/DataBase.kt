import java.util.*
import java.util.concurrent.ConcurrentHashMap

class DataBase {
    private var hash : ConcurrentHashMap<String,Boolean>

    constructor(uLimit: Int){
        hash = generateHash(uLimit);
    }

    private fun generateHash(uLimit: Int): ConcurrentHashMap<String,Boolean>{
        var hash = ConcurrentHashMap<String,Boolean>(uLimit)
        var random = Random();
        for(i in 0..uLimit-1){
            var str: String = "";
            do {
                str = "";
                for (j in 0..9)
                    str += Integer.toHexString(random.nextInt(16));
            } while (hash.containsKey(str))
            hash.put(str,false);
        }
        return hash;
    }

    @Synchronized
    fun getUID(): String? {
        for(item in hash)
            if(item.value == false){
                hash.put(item.key,true)
                return item.key
            }
        return null;
    }

    @Synchronized
    fun returnUID(uid: String){
        hash.put(uid,false)
    }
}