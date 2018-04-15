package main

import (
    "fmt"
)

func BinarySearch01(arr []int) int {
    size := len(arr)
    if size == 1 && arr[0] == 0 {
        return -1
    }

    if arr[0] == 1 {
        return 0
    }

    return BinarySearch01Until(arr, 0, size-1)
}

func BinarySearch01Until(arr []int, start int, end int) int {
    if end < start {
        return -1
    }

    mid := (start+end)/2

    if 1 == arr[mid] && 0 == arr[mid-1] {
        return mid
    }

    if 0 == arr[mid] {
        return BinarySearch01Until(arr, mid+1, end)
    }

    return BinarySearch01Until(arr, start, mid-1)
}


func main() {
    arr := []int {0,0,0,0,0,0,0,0,0,1,1,1,1,1,1}
    fmt.Println(BinarySearch01(arr) == 9)

    arr = []int {0,0,0,0,0,1}
    fmt.Println(BinarySearch01(arr) == 5)

    arr = []int {1}
    fmt.Println(BinarySearch01(arr) == 0)

    arr = []int {1,1,1,1,1}
    fmt.Println(BinarySearch01(arr) == 0)

    arr = []int {0}
    fmt.Println(BinarySearch01(arr) == -1)

    arr = []int {0,0,0,0,0,0}
    fmt.Println(BinarySearch01(arr) == -1)
}
