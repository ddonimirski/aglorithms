package main

import (
    "fmt"
)

func separateEvenAndOdd(data []int) {
    size := len(data)
    left := 0
    right := size-1

    for left < right {
        if data[left]%2 == 0 {
            left++
        } else if data[right]%2 == 1 {
            right--
        } else {
            data[left],data[right] = data[right], data[left]
            left++
            right--
        }
    }
}

func main() {
    arr := []int {1,2,3,4,5,5,5,5,6,6,6,7,7,7,8}
    separateEvenAndOdd(arr)
    for _, v:= range arr {
        fmt.Print(v," ")
    }
    fmt.Println()
}
