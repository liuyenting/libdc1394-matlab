#ifndef DC1394_HPP
#define DC1394_HPP

class dc1394
{
public:
	// init/deinit the library object
	dc1394();
	~dc1394();

	// enumerate all valid cameras
	void enumerate_cameras();

	// connect/disconnect camera
	void connect();
	void disconnect();

	// capture frame
	void capture();

private:
};

#endif
