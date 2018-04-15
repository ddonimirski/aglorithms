package main

import (
    "fmt"
   )


func printProfit(buy, sell, maxPro int, stocks []int) {
    fmt.Println("Purchase day is- ", buy, " at price ",stocks[buy])
    fmt.Println("Sell day is- ", sell, " at price ", stocks[sell])
    fmt.Println("Max Profit: ", maxPro)
}


func maxProfit(stocks []int) {

    size := len(stocks)
    buy := 0
    sell := 0
    maxPro := 0
   
    for i:= 0; i<size; i++ {
        for j:=1; j<size; j++ {
            curProfit := stocks[j] - stocks[i]
            if maxPro < curProfit {
                buy = i
                sell = j
                maxPro = curProfit
            }
        }
    }

    printProfit(buy, sell, maxPro, stocks)
}

func maxProfit2(stocks []int) {

    size := len(stocks)
    buy := 0
    sell := 0
    curMin := 0
    currProfit := 0
    maxPro:= 0

    for i:=0; i<size; i++ {
        if stocks[i] < stocks[curMin] {
            curMin = i
        }

        currProfit = stocks[i] - stocks[curMin]
        if maxPro < currProfit {
            buy = curMin
            sell = i
            maxPro = currProfit
        }
    }

    printProfit(buy, sell, maxPro, stocks)
}

func main() {

    arr := []int{1,2,3,4,3,4,5,6,78,3,2,5,7,82,1,3,45,12}
    maxProfit(arr)
    maxProfit2(arr)
}
