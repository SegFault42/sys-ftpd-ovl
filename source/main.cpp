#define TESLA_INIT_IMPL // If you have more than one file using the tesla header, only define this in the main one
#include <tesla.hpp>    // The Tesla Header

//void debug()
//{
    //Result rc;
    //rc = fsInitialize();
    //if (R_FAILED(rc))
        //fatalThrow(MAKERESULT(Module_Libnx, LibnxError_InitFail_FS));

    //fsdevMountSdmc();
    //FILE *fp = fopen("/test", "a+");
    //if (fp != NULL) {
        //fclose(fp);
    //}
	//fsdevUnmountAll();
    //fsExit();

//}

char hostname[128] = {0};

class GuiTest : public tsl::Gui {
	public:
    	GuiTest() { }

    	// Called when this Gui gets loaded to create the UI
    	// Allocate all elements on the heap. libtesla will make sure to clean them up when not needed anymore
    	virtual tsl::elm::Element* createUI() override {
        	auto frame = new tsl::elm::OverlayFrame("sys-ftpd-ovl", "v1.0.0");

        	// A list that can contain sub elements and handles scrolling
        	auto list = new tsl::elm::List();

        	list->addItem(new tsl::elm::ListItem("Ip : ", hostname));

        	// Create and add a new list item to the list

        	// Add the list to the frame for it to be drawn
        	frame->setContent(list);

        	// Return the frame to have it become the top level element of this Gui
        	return frame;
    	}

    	// Called once every frame to update values
    	virtual void update() override {

    	}

    	// Called once every frame to handle inputs not handled by other UI elements
    	virtual bool handleInput(u64 keysDown, u64 keysHeld, touchPosition touchInput, JoystickPosition leftJoyStick, JoystickPosition rightJoyStick) override {
        	return false;   // Return true here to singal the inputs have been consumed
    	}
};

class OverlayTest : public tsl::Overlay {
	public:
        // libtesla already initialized fs, hid, pl, pmdmnt, hid:sys and set:sys
    	virtual void initServices() override {
    	}  // Called at the start to initialize all services necessary for this Overlay
    	virtual void exitServices() override {
    	}  // Callet at the end to clean up all services previously initialized

    	virtual void onShow() override {
    		// Get Ip address
			tsl::hlp::doWithSmSession([]{
				gethostname(hostname, sizeof(hostname));
            });
    	}    // Called before overlay wants to change from invisible to visible state
    	virtual void onHide() override {}    // Called before overlay wants to change from visible to invisible state

    	virtual std::unique_ptr<tsl::Gui> loadInitialGui() override {
        	return initially<GuiTest>();  // Initial Gui to load. It's possible to pass arguments to it's constructor like this
    	}
};

int main(int argc, char **argv) {
    return tsl::loop<OverlayTest>(argc, argv);
}
