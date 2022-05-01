#include <stdexcept>
#include <iostream>
#include <exception>

#include <boost/exception/all.hpp>
#include <boost/stacktrace.hpp>

struct FirstIOException : std::runtime_error {
	FirstIOException(std::string what) : std::runtime_error(what) {}
};

struct SecondIOException : std::runtime_error {
	SecondIOException(std::string what) : std::runtime_error(what) {}
};

struct ThirdIOException : boost::exception {};

typedef boost::error_info<struct tag_filename, std::string> filename;
typedef boost::error_info<struct tag_stacktrace, boost::stacktrace::stacktrace> stacktrace;

void print_nested_exceptions(std::exception& e) {
	try {
		std::cerr << e.what() << "\n";
		std::rethrow_if_nested(e);
	}
	catch (std::exception &e) {
		print_nested_exceptions(e);
	}
}

void ll_open_file() {
	throw FirstIOException("ll_open_file() failed");
}

void open_file() {
	try {
		ll_open_file();
	}
	catch (std::exception &e) {
		throw boost::enable_error_info(e)
			<< filename("asdf.txt");
	}
}

void some_function() {
	try {
		open_file();
	}
	catch (boost::exception &e) {
		e << stacktrace(boost::stacktrace::stacktrace());
		throw;
	}
}

int main(int argc, char** argv) {
	try {
		some_function();
	}
	catch (std::exception &e) {
		 auto info = boost::diagnostic_information(e);
		 std::cerr << info << "\n";
	}
}