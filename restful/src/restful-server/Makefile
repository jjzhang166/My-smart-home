GO ?= go
GOPATH := $(CURDIR)/_vendor:$(CURDIR)/../..:$(GOPATH)

all: restful-server

restful-server:
		$(GO) build -v -o $@

clean:
		-rm -f restful-server
