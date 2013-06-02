package org.deadcode.wmelite;

public class WMELiteFunctions {

	public native void nativeInit();
	
	public String getLogFileDirectory() {
		// FIXME needs proper path detection
		return "/mnt/sdcard";
	}
	
	public String getPrivateFilesPath() {
		// FIXME create a Java callback to retrieve the path
		return "/data/data/org.libsdl.app/files/";
		
	}

	public String getDeviceTypeHint() {
		// FIXME ask Android about screen size and decide
		return "tablet";
		
	}

	public String getGamePackagePath() {
		// FIXME create a Java callback to retrieve the path
		return "/mnt/sdcard/";
		
	}

	public String getGameFilePath() {
		// FIXME create a Java callback to retrieve the path
		return "/mnt/sdcard/";
		
	}

	public String getFontPath() {
		// FIXME create a Java callback to retrieve the path
		return "/data/data/org.libsdl.app/assets/fonts/";
		
	}
}
