package myhash

import (
	"errors"
	"fmt"
	"math/rand"
	"sort"
)

type ConstantHash struct {
	cycle    map[int]string
	maxint   int32
	realSize int
	hashNode []int
}

func (hash *ConstantHash) Init(maxint int32) {
	hash.maxint = maxint
	hash.cycle = make(map[int]string)
	hash.hashNode = make([]int, 0)
}

// dataList, ip池
// virtualNode, 虚拟节点
// weigtList，权重
func (hash *ConstantHash) InitHashCycle(dataList []string, virtualNodeNum int32, weigtList []int32) error {
	if len(dataList) == 0 {
		return errors.New("data List is nil")
	}

	hash.realSize = len(dataList)
	if len(weigtList) == 0 {
		weigtList = hash.defauleWeight(weigtList)
	} else if hash.realSize != len(weigtList) {
		return errors.New("data list not match weight list")
	}

	fmt.Println("weight List:", weigtList)

	for idx, serverNode := range dataList {
		totalNode := virtualNodeNum * weigtList[idx]
		for j := 0; j < int(totalNode); j++ {
			// 生成虚拟节点，指向同一个ip
			hash.addData(serverNode)
		}
	}

	sort.Ints(hash.hashNode)
	fmt.Println("constant hash:", hash)
	fmt.Println("sort hash node:", hash.hashNode)

	return nil
}

func (hash *ConstantHash) defauleWeight(weigtList []int32) []int32 {
	fmt.Println("hash size:", hash.realSize)
	for i := 0; i < hash.realSize; i++ {
		weigtList = append(weigtList, 1)
	}
	return weigtList
}

func (hash *ConstantHash) FindAimNodeByHashNode(aimNode int32) (int, string) {
	// 查找顺时针指向最近的realNode
	serverNode, isok := hash.cycle[int(aimNode)]
	if isok {
		return int(aimNode), serverNode
	}

	for _, virtualNode := range hash.hashNode {
		if virtualNode > int(aimNode) {
			return virtualNode, hash.cycle[virtualNode]
		}
	}

	return 0, hash.cycle[0]
}

func (hash *ConstantHash) AddServerNode(serverNode string, virtualNode, weight int32) {
	totalInsertNode := virtualNode * weight
	for i := 0; i < int(totalInsertNode); i++ {
		hash.addData(serverNode)
	}
	sort.Ints(hash.hashNode)
	fmt.Println("constant hash:", hash)
	fmt.Println("sort hash node:", hash.hashNode)
}

func (hash *ConstantHash) addData(serverNode string) {
	for {
		insertNode := rand.Int31n(hash.maxint)
		data, isok := hash.cycle[int(insertNode)]
		if !isok {
			hash.cycle[int(insertNode)] = serverNode
			hash.hashNode = append(hash.hashNode, int(insertNode))
			return
		}
		if data == serverNode {
			return
		}
	}
}

func (hash *ConstantHash) RemoveServerNodeByHashNode(hashNode int) {
	delete(hash.cycle, hashNode)
	for idx, virtualNode := range hash.hashNode {
		if virtualNode == hashNode {
			hash.hashNode = append(hash.hashNode[:idx], hash.hashNode[idx+1:]...)
		}
	}
	fmt.Println("constant hash:", hash)
	fmt.Println("sort hash node:", hash.hashNode)
}

func (hash *ConstantHash) RemoveServerNodeByData(serverData string) {
	for key, val := range hash.cycle {
		if val == serverData {
			for idx, virtualNode := range hash.hashNode {
				if virtualNode == key {
					hash.hashNode = append(hash.hashNode[:idx], hash.hashNode[idx+1:]...)
				}
			}
			delete(hash.cycle, key)
		}
	}

	fmt.Println("constant hash:", hash)
	fmt.Println("sort hash node:", hash.hashNode)
}
