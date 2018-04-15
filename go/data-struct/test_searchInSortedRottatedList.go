package main

import (
    "fmt"
)

func BinarySearchRotateArray(data []int, key int) int {
    size := len(data)
    return BinarySearchRotateArrayUntil(data, 0, size-1, key)
}

func BinarySearchRotateArrayUntil(arr []int, start int, end int, key int) int {
    if end < start {
        return -1
    }

    mid := (start+end)/2

    if key == arr[mid] {
        return mid
    }

    if arr[mid] > arr[start] {
        if arr[start]<=key && key<arr[mid] {
            return BinarySearchRotateArrayUntil(arr, start, mid-1, key)
        }
        return BinarySearchRotateArrayUntil(arr, mid+1, end, key)
    } else {
        if arr[mid]<key && key<=arr[end] {
            return BinarySearchRotateArrayUntil(arr, mid+1, end, key)
        }
        return BinarySearchRotateArrayUntil(arr, start, mid-1, key)

    }
}

//Not work

func main() {
    arr := []int {7,6,5,4,3,2,1}
    fmt.Println(BinarySearchRotateArray(arr, 2))

    arr = []int {1,2,3,4,5,6,7}
    fmt.Println(BinarySearchRotateArray(arr, 2))
}

