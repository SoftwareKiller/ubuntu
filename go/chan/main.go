package main

import "chan/gotask"

func main() {
	// game.Game()
	// msgqueue.Start()
	/*var b bytes.Buffer
	b.Write([]byte("Hello"))
	fmt.Fprintf(&b, " World! Mac CPU:%v\n", runtime.NumCPU())
	io.Copy(os.Stdout, &b)
	insettype.InsetTest()
	gotask.GoTask()*/
	gotask.Call()
}
