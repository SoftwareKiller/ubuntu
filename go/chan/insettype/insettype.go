package insettype

import "fmt"

type user struct {
	Name string
	Age  int
}

type notify interface {
	notify()
}

func (u *user) notify() {
	fmt.Printf("Name:%s Age:%d\n", u.Name, u.Age)
}

type addmin struct {
	user
	level int32
}

func (ad *addmin) notify() {
	fmt.Printf("Name:%s Age:%d level:%d\n", ad.Name, ad.Age, ad.level)
}

func InsetTest() {
	ad := addmin{
		user: user{
			Name: "Jay",
			Age:  18,
		},
		level: 1,
	}
	sendnotify(&ad.user)
	sendnotify(&ad)
}

func sendnotify(n notify) {
	n.notify()
}
