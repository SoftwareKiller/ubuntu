package tennis

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

var wg sync.WaitGroup

func init() {
	rand.Seed(time.Now().UnixNano())
}

func Game() {
	// 网球场
	court := make(chan int, 10)

	wg.Add(2)

	go player("jay", court)
	go player("luca", court)

	court <- 1

	wg.Wait()
}

func player(name string, court chan int) {
	defer wg.Done()
	for {
		ball, ok := <-court
		if !ok {
			fmt.Printf("Player :%s Won!\n", name)
			return
		}

		// 模拟随机数
		n := rand.Intn(10000)
		if n%999 == 0 {
			fmt.Printf("Player :%s Missed\n", name)
			close(court)
			return
		}

		// 击球
		fmt.Printf("Player :%s Hit %d\n", name, ball)
		ball++
		court <- ball
	}
}
