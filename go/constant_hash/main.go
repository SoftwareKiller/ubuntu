package main

import (
	"constant/myhash"
	"fmt"
)

func main() {
	fmt.Println("start Constant Hash")
	var hash myhash.ConstantHash
	var ipPool []string
	ipPool = append(ipPool, "127.0.0.1")
	ipPool = append(ipPool, "127.0.0.2")
	ipPool = append(ipPool, "127.0.0.3")
	ipPool = append(ipPool, "127.0.0.4")
	hash.Init(100)
	err := hash.InitHashCycle(ipPool, 10, nil)
	if err != nil {
		fmt.Println("err msg:", err)
	}

	hashKey, val := hash.FindAimNodeByHashNode(20)
	fmt.Println("hash find:", hashKey, val)
	hash.AddServerNode("127.0.0.5", 1, 1)
	hash.RemoveServerNodeByHashNode(hashKey)
	hash.RemoveServerNodeByData("127.0.0.1")
}
