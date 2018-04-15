package main

import (
    "fmt"
    "sort"
)

func findKeyCount(data []int, key int) int {
    count := 0
    size := len(data)
    for i:=0; i<size; i++ {
        if data[i] == key {
            count++
        }
    }

    return count
}

func findKeyCount2(data []int, key int) int {
    size := len(data)
    firstIndex := findFirstIndex(data, 0, size-1, key)
    secondIndex := findLastIndex(data, firstIndex, size-1, key)
    return (secondIndex - firstIndex + 1)
}

func findFirstIndex(data []int, begin int, end int, key int) int {
    if end < begin {
        return -1
    }

    mid := (begin+end)/2
    if key == data[mid] && (mid == begin || data[mid-1]!= key) {
        return mid
    }

    if key <= data[mid] {
        return findFirstIndex(data, begin, mid-1, key)
    }

    return findFirstIndex(data, mid+1, end, key)
}

func findLastIndex(data []int, begin int, end int, key int) int {
    if end < begin {
        return -1
    }

    mid := (begin + end)/2

    if key == data[mid] && (mid == end || data[mid+1]!=key) {
        return mid
    }

    if key <= data[mid] {
        return findFirstIndex(data, begin, mid-1, key)
    }

    return findFirstIndex(data, mid+1, end, key)
}

func main() {
    arr := []int {1,2,3,4,5,5,5,5,6,6,6,7,7,7,8}
    sort.Ints(arr)
    fmt.Println(findKeyCount(arr, 5) == 4)
    fmt.Println(findKeyCount2(arr, 5))
}
