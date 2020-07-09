# KFRandomizer manual
Right now, using KFRandomizer is a bit confusing. So I've written this guide to try and help make the process a bit more understandable.

You're going to need a few things to follow this guide:
* A computer running 64-bit Windows or Linux 
* The latest build of KFRandomizer (we'll talk about how to get that in a bit)
* CDmage 1.02.1 (you can download it [here!](https://www.videohelp.com/download/CDmage1-02-1B5.exe))
* Wine, if you're under Linux, for running CDmage

You can probably follow this tutorial under macOS by using Wine for both CDmage and a Windows build of KFRandomizer.

## Getting the latest build of KFRandomizer
To download the latest build of KFRandomizer, head on over to the project's [GitHub Actions page](https://github.com/IvanDSM/KingsFieldRE/actions). Once you're there, click on the first item in the "All workflows" list. In the image below, the latest build at the time of writing is highlighted in green. Follow the link in that position.

![GitHub Actions page. Don't mind the message inside the green highlight, what matters is the position!](https://github.com/IvanDSM/KingsFieldRE/blob/master/wiki/kfrandomizer_manual/get_latest_build.png)

You'll arrive at the GitHub Actions page for that run. A variety of tools will be available here, but you just need to download te appropriate build for your system. Select the correct one from the list of builds as highlighted in green in the picture below:

![GitHub Actions page for the latest run. Note the KFRandomizer builds!](https://github.com/IvanDSM/KingsFieldRE/blob/master/wiki/kfrandomizer_manual/actions_build.png)

Unpack the files in a folder of your choice. After that, run the KFRandomizer executable (KFRandomizer on Linux, KFRandomizer.exe on Windows). You'll get a screen like this:

![Randomizer UI as of writing](https://github.com/IvanDSM/KingsFieldRE/blob/master/wiki/kfrandomizer_manual/randomizer.png)

You will notice the randomizer is asking for an FDAT.T file. This is a file that's inside the King's Field CD. To obtain and replace this file, we'll use CDmage.

## Getting FDAT.T with CDmage
First, copy your King's Field CD image somewhere else. This copy will be the image we'll randomize. Next up, open CDmage. You'll be greeted by a screen like the one below:

![CDmage without any file loaded](https://github.com/IvanDSM/KingsFieldRE/blob/master/wiki/kfrandomizer_manual/cdmage.png)

Drag your image's .cue file or open it by going to File -> Open... and you'll get something like this:

![CDmage with the our image loaded](https://github.com/IvanDSM/KingsFieldRE/blob/master/wiki/kfrandomizer_manual/cdmage_loaded.png)

(If you don't see "Track 1" on the left side, double click "Session 1".)

Double click "Track 1". "CD" and "OP" will appear under it. Double click "CD". "COM" will appear under "CD". Double click "COM". Your CDmage screen should look like this:

![CDmage screen with the COM folder open](https://github.com/IvanDSM/KingsFieldRE/blob/master/wiki/kfrandomizer_manual/cdmage_com.png)

Right-click FDAT.T then click "Extract files...". CDmage will ask you what folder to extract. Choose a folder of your choice and hit Extract. Now keep CDmage open and let's head back to the randomizer!

## Randomizing FDAT.T
Now we're ready to randomize! In the randomizer, click "click to choose..." where it says "Your FDAT.T file:" and pick the FDAT.T file we just extracted. Choose what options you want for the randomizer and then click "Randomize!". The program will copy FDAT.T to its memory and randomize it according to your chosen options, and when it's done it'll let you know.

The program will then ask you where to save the randomized FDAT.T. You can name it anything but I'd advise you to choose wisely. Once you've saved it, let's switch back to CDmage.

## Patching your CD image
Now we're back in CDmage, right-click FDAT.T and click "Import File...". Select the randomized FDAT.T that you saved in the last step. That's it! Now you can run your copy of the image in an emulator or burn it to a disc and play it on a modded PlayStation! Have fun :)

Do you think this guide could be improved? [Open an issue](https://github.com/IvanDSM/KingsFieldRE/issues/new/choose) with your suggestions! :D