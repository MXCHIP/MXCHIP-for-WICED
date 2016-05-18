# WICED for MXCHIP wireless modules
*Supports EMW3162 and EMW3165*

*Use sales@mxchip.com to contact MXCHIP*

##Using method
* Download WICED-SDK-3.5.2.7z.zip from Broadcom. It requires registration on their site **with what Broadcom calls a "corporate" e-mail address, so you can't use GMail, Outlook.com or other such e-mail addresses**.

###Using git and apply patch file
* Create a git repository for WICED-SDK-3.5.2
* Place the file in patchs directory and run `git apply mxchip_for_wiced_3.5.2_patch` with git command. This will decompress and patch WICED SDK.
* Enter the WICED-SDK-3.5.2 directory and run something like `./make EMW<module no>-<app-dir>.<app-name> download run JTAG=<jtag-adapter>` to compile and flash.

###Or replace target files manually
* Add the file `EMW3162`,`EMW3165` in patchs directory to the WICED-SDK-3.5.2 directory `WICED-SDK\platforms`.
* Replace the same files in the `WICED-SDK\tools\OpenOCD` folder with the file in the `patchs\OpenOCD` folder. 

###Then
* Change into the SDK directory with `cd WICED-SDK-3.5.2`
* Test flashing an application to the module.

For EMW3162, using stlink-v2 for flashing, using the application *scan* from the *snip* directory run:
`./make EMW3162-snip.scan download run JTAG=stlink-v2`

For EMW3165, using stlink-v2 for flashing, using the application *scan* from the *snip* directory run:
`./make EMW3165-snip.scan download run JTAG=stlink-v2`

You may need to hold down reset while starting the flashing process while using st-link-v2.

* If the step above is successful, you should be able to see output via UART and see the list of Wi-Fi around.
* You can now start playing around. WICED comes with loads of sample application, so, look around, hack around and make stuff happen.
* Please contact us if you experience any issues getting up and running.
