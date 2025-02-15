build-app:
	@clang++ -std=c++20 app.cpp -o app
	./app

build-app-server:
	@clang++ -std=c++20 http-server/src/main.cpp -o app-server
	./app-server 8090