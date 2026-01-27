package main


//TODO CHANGE ADD LOGIC TO INCLUDE KEY AND FIND OUT HOW TO PASS ADDRESS OF POINTER

import (
	"fmt"
	"time"
)

const(
	MAX_LEN = 10

)


type Bucket struct{
	data uint8
	link *Bucket
}

func main() {
	t0 := time.Now()
	arr := [MAX_LEN]uint8{20,15,10,30,12,23,84,91,02,19}
	radixSort(arr)
	printArr(arr)
	
	fmt.Printf("Total time of execution: %v", time.Since(t0))
}

func add(key uint8, val uint8, head** Bucket){
	var ndx **Bucket
	for ndx = head; *ndx != nil; ndx = &((*ndx).link){}
	*ndx = new(Bucket)
	(*ndx).data = val
}

func delete(head** Bucket) uint8{
	if *head == nil{
		return 255
	}

	var temp *Bucket = *head
	*head = temp.link
	retVal := temp.data
	temp = nil
	return retVal
}


/*
* Constraints:
* two digit number for now
* array is fixed length of 10
*/
func radixSort(arr [10]uint8) {
	head := make([]*Bucket, 10)
	var radix uint8 = 10

	for i := 0; i < 2; i++{
		
		for _, i := range arr{
			add(i%radix, i, &head)
		}
	
		idx := 0
		for ndx := 0; ndx < MAX_LEN; ndx++{
		  for head[ndx] != nil {
				arr[idx] = delete(&(head[ndx])
				idx++;
			}
		}
		radix *= 10
	} 
}

func printArr(arr [10]uint8){
	for _, i := range arr{
		fmt.Printf("%v ", i)
	}
}
