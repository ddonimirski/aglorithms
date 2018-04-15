package main

import (
    "fmt"
    "sort"
)

func findMedian(arr []int) int {
    size := len(arr)
    sort.Ints(arr)
    return arr[size/2]
}

func findMedianOfTwoSorted(dataFirst []int, dataSecond []int) int {
    sizeFirst := len(dataFirst)
    sizeSecond := len(dataSecond)

    medianIndex := ((sizeFirst+sizeSecond) + (sizeFirst+sizeSecond)%2)/2
    i := 0
    j := 0
    count := 0
    for count < medianIndex-1 {
        if i < sizeFirst-1 && dataFirst[i] < dataSecond[j] {
            i++
        } else {
            j++
        }
        count++
    }

    if dataFirst[i] < dataSecond[j] {
        return dataFirst[i]
    }
    return dataSecond[j]
}


func main() {
    arr1 := []int {1,2,3,4,2,2,3,4,5,4,5,6,7,8,9,6,4,5,6,3,2,1,3,3,4,5,7}

    fmt.Println("Median ", findMedian(arr1))

    arr2 := []int {1,1,1,1,2,2,3,4,1,1,1}
    sort.Ints(arr2)

    fmt.Println("Median of two ", findMedianOfTwoSorted(arr1,arr2))
}
