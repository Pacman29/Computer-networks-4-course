import java.util.*
import kotlin.collections.ArrayList

fun sorter(arrayList: ArrayList<String>, keyWord: String) : ArrayList<String> {
    var newArray = ArrayList<String>()
    for(s in arrayList)
        if(keyCounter(s,keyWord, true) > 0)
            newArray.add(s)
    Collections.sort(newArray){ x, y ->  keyCounter(x,keyWord,false) - keyCounter(y,keyWord, false) }
    return newArray;
}

fun keyCounter(s: String, key: String, debug: Boolean): Int {
    var splited = s.split(" ");
    var count = 0
    for (word in splited){
        if(word.equals(key,true))
            count++
    }
    if(debug){
        println(s)
        println(count)
    }

    return count
}