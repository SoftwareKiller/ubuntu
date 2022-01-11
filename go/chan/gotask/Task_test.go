package gotask

import (
	"fmt"
	"sync/atomic"
	"testing"
	"time"
)

func TestTask(t *testing.T) {
	wg.Add(2)

	go incCounter()
	go incCounter()

	wg.Wait()
	fmt.Println("counter:", counter)
}

func TestWork(t *testing.T) {
	wg.Add(2)
	go doWork("A")
	go doWork("B")

	time.Sleep(1 * time.Second)

	atomic.StoreInt64(&shutdown, 1)

	wg.Wait()
}

func TestMutiChan(t *testing.T) {
	wg.Add(10)

	tasks := make(chan string, 10)

	for i := 0; i < 10; i++ {
		go mutiChanDoWork(tasks, i)
	}

	for i := 0; i < 10; i++ {
		tasks <- fmt.Sprintf("%d", i)
	}

	close(tasks)

	wg.Wait()
}
