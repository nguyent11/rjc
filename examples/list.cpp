/**************************************************************************************************
 * Example that creates a list of usb devices and accesses information held in the device
 * descriptors. Uses the libusb library.
 *
 * Dependency:
 * 	libusb 1.0.25: Install with 'apt-get install libusb-1.0-dev'
 *
 * To run:
 * 	g++ list.cpp -lusb-1.0
 *************************************************************************************************/
 

#include <stdio.h>
#include <libusb-1.0/libusb.h>

int main(int argc, char* argv[]) {
    libusb_device **devices;	// List of devices
    libusb_context *ctx = NULL;
    ssize_t count;
    int ret;

    // Initialize libusb
    ret = libusb_init(&ctx);
    if (ret < 0) {
        fprintf(stderr, "Failed to initialize libusb: %s\n", libusb_error_name(ret));
        return 1;
    }

    // Get list of USB devices
    count = libusb_get_device_list(ctx, &devices);
    if (count < 0) {
        fprintf(stderr, "Error getting device list: %s\n", libusb_error_name(count));
        libusb_exit(ctx);
        return 1;
    }

    printf("Found %zd USB devices:\n", count);

    // Iterate through devices
    for (ssize_t i = 0; i < count; i++) {
        libusb_device *device = devices[i];
        struct libusb_device_descriptor desc;

        // Get device descriptor
        ret = libusb_get_device_descriptor(device, &desc);
        if (ret < 0) {
            fprintf(stderr, "Failed to get device descriptor: %s\n", libusb_error_name(ret));
            continue;
        }

        printf("Device %zd: Vendor ID: 0x%04x, Product ID: 0x%04x, Bus %03d, Device %03d, USB-IF class code: %03d, USB-IF sub-class code: %03d\n",
               i, desc.idVendor, desc.idProduct,
               libusb_get_bus_number(device),
               libusb_get_device_address(device), desc.bDeviceClass, desc.bDeviceSubClass);
    }

    // Free the list, unref devices
    libusb_free_device_list(devices, 1);

    // Cleanup libusb
    libusb_exit(ctx);
    return 0;
}
