basepath=$(cd `dirname $0`; pwd)
mkdir $basepath/src -p
$basepath/../../opt/protobuf_linux/bin/protoc --cpp_out=./src/ *.proto
