package main

import (
	"fmt"
	"time"
)

type Bucket struct{
	data uint8
	link *List
}

func main() {
	t0 := time.Now()
	arr := []uint8{20,15,10,30}
	radixSort(arr)

	fmt.Printf("Total time of execution: %v", time.Since(t0))
}

func add(val uint8, head** Bucket){
	var ndx **Bucket
	for ndx = head; *ndx != nil; ndx = &((*ndx).link){}
	*ndx = new(Bucket)
	(*ndx).data = val
}

func delete(head** Bucket) uint8{
	if *head == nil{
		return 255
	}

	var temp *Bucket = 

}


func radixSort(arr []uint8) {
	var head *Bucket = new(Bucket) //nil by default

	
}
