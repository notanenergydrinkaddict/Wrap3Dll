# Wrap3Dll

Quality of Life modifications for Wrap3 (Win32 only)

# Features

- Sync Views enabled on node create:
  - `SelectPointPairs`
  - `SelectPointPairsWithSplines`

# Install

- Download [Ultimate-ASI-Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases/download/x64-latest/version-x64.zip)
- Download [`Wrap3Dll.zip`](https://github.com/notanenergydrinkaddict/Wrap3Dll/releases/latest/download/Wrap3Dll.zip)
    - Navigate to
    ```
    C:\Program Files\Faceform
    ```
    - Go into Wrap folder, i.e `Wrap 2024.11.10`
    - Extract `version.dll` from downloaded `version-x64.zip` to Wrap install folder.
    - Extract `Wrap3Dll.asi` from downloaded `Wrap3Dll.zip` to Wrap Install folder.
    - Folder should look like this:
      ```
      PS C:\Program Files\Faceform\Wrap 2024.11.10> ls

      Directory: "C:\Program Files\Faceform\Wrap 2024.11.10"

      Mode                 LastWriteTime         Length Name
      ----                 -------------         ------ ----
      d-----         11/26/2024  1:24 PM                Fonts
      d-----         11/26/2024  1:24 PM                Gallery
      d-----         11/26/2024  1:24 PM                lib
      d-----         11/26/2024  1:24 PM                plugins
      ------
      -a----         8/15/2025   6:30 AM        1041408 version.dll
      -a----        11/26/2024  11:07 PM       32203696 Wrap.exe
      -a----         8/20/2025   1:37 PM          22528 Wrap3Dll.asi
      ```
- Launch Wrap and pick the nodes from above, Sync Views should be enabled by default.

# Credits

- [illusiony](https://github.com/illusion0001) for [Windows-Game-Patches](https://github.com/illusion0001/Windows-Game-Patches) used as a base for this project.
