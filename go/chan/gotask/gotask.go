package gotask

import (
	"fmt"
	"math/rand"
	"runtime"
	"sync"
	"sync/atomic"
	"time"
)

func init() {
	rand.Seed(time.Now().Unix())
}

func GoTask() {
	//runtime.GOMAXPROCS(1)
	var wg sync.WaitGroup
	wg.Add(2)

	go func() {
		defer wg.Done()
		for i := 0; i < 3; i++ {
			for c := 'a'; c < 'a'+26; c++ {
				fmt.Printf("%c ", c)
			}
		}
		fmt.Println()
	}()

	go func() {
		defer wg.Done()
		for i := 0; i < 3; i++ {
			for c := 'A'; c < 'A'+26; c++ {
				fmt.Printf("%c ", c)
			}
		}
		fmt.Println()
	}()

	wg.Wait()
}

var (
	counter  int64
	wg       sync.WaitGroup
	shutdown int64
)

func Call() {
	wg.Add(2)

	// condition race
	//go incCounter()
	//go incCounter()

	// security
	go atomicIncCounter()
	go atomicIncCounter()

	wg.Wait()
	fmt.Println("counter:", counter)
}

func incCounter() {
	defer wg.Done()

	for i := 0; i < 2; i++ {
		value := counter
		runtime.Gosched()
		value++
		counter = value
	}
}

func atomicIncCounter() {
	defer wg.Done()

	for i := 0; i < 2; i++ {
		atomic.AddInt64(&counter, 1)
	}
}

func doWork(name string) {
	defer wg.Done()

	for {
		fmt.Println(name)
		time.Sleep(200 * time.Millisecond)
		if atomic.LoadInt64(&shutdown) == 1 {
			break
		}
	}
}

func mutiChanDoWork(tasks chan string, workID int) {
	defer wg.Done()

	for {
		task, ok := <-tasks
		if !ok {
			fmt.Printf("Work goroutine:%d shutdown!\n", workID)
			return
		}

		fmt.Printf("workID:%d start process task:%s\n", workID, task)
		sleep := rand.Int31n(100)
		time.Sleep(time.Duration(sleep) * time.Millisecond)
		fmt.Printf("workID:%d complate task:%s\n", workID, task)
	}
}
