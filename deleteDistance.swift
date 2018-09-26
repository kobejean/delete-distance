import Foundation

func deletionDistance(str1: String, str2: String) -> Int {
  // initialization
  var D = [[Int]]()
  let (n, m) = (str1.characters.count+1, str2.characters.count+1)
  D.reserveCapacity(n)
  for i in 0..<n {
    var column = [Int]()
    column.reserveCapacity(m)
    for j in 0..<m {
      if (i == 0 || j == 0) {
        column.append(i + j)
      } else {
        column.append(str1.characters.count + str2.characters.count)
      }
    }
    D.append(column)
  }


  for i in 1..<n {
    for j in 1..<m {
      let idx1 = str1.index(str1.startIndex, offsetBy: i-1)
      let idx2 = str2.index(str2.startIndex, offsetBy: j-1)
      let inc_SW = (str1[idx1] == str2[idx2]) ? 0 : 2
      let inc_S = 1
      let inc_W = 1
      D[i][j] = min(D[i-1][j-1] + inc_SW, D[i][j])
      D[i][j] = min(D[i-1][j  ] + inc_S, D[i][j])
      D[i][j] = min(D[i  ][j-1] + inc_W, D[i][j])

    }
  }
  // print(D)
  return D[str1.characters.count][str2.characters.count]
}

// print(deletionDistance(str1:"hit", str2:"heat"))
// print(deletionDistance(str1:"some", str2:"thing"))
// print(deletionDistance(str1:"", str2:""))
