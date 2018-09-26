import Foundation

func deletionDistance(str1: String, str2: String) -> Int {
  var str_1 = str1
  var str_2 = str2
  if (str1.characters.count < str2.characters.count) {
    let tmpStr = str1
    str_1 = str2
    str_2 = tmpStr
  }
  let n = str_1.characters.count
  let m = str_2.characters.count
  var prevRow = [Int]()
  prevRow.reserveCapacity(m + 1)
  var currRow = [Int]()
  currRow.reserveCapacity(m + 1)
  for i in 0...n {
    for j in 0...m {
      if (i == 0) {
        currRow.append(j)
      } else if (j == 0) {
        currRow.append(i)
      } else {
        let idx1 = str_1.index(str_1.startIndex, offsetBy: i-1)
        let idx2 = str_2.index(str_2.startIndex, offsetBy: j-1)
        if (str_1[idx1] == str_2[idx2]) {
          currRow.append(prevRow[j-1])
        } else {
          currRow.append(1 + min(prevRow[j], currRow[j-1]))
        }
      }
    }
    prevRow = currRow
    currRow = [Int]()
    currRow.reserveCapacity(m + 1)
  }
  return prevRow[m];
}

// print(deletionDistance(str1:"hit", str2:"heat"))
// print(deletionDistance(str1:"some", str2:"thing"))
// print(deletionDistance(str1:"", str2:""))
