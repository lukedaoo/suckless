Download the 6.5 tarball (for diff baseline):

Go to https://dl.suckless.org/dwm/ and grab dwm-6.5.tar.xz. Extract it:
```
tar -xf dwm-6.5.tar.xz
cd dwm-6.5
```

Create diff from your current 6.5 build:

From your existing dwm source dir (the patched 6.5 one), run:
```
diff -urN dwm-6.5/ your-patched-dwm-dir/ > dwm-patches.diff
```
This generates a single patch file with all your changes.

Download and extract 6.6:

From https://dl.suckless.org/dwm/, get dwm-6.6.tar.xz:
```
tar -xf dwm-6.6.tar.xz
cd dwm-6.6
```

Apply your patches:
```
patch -p1 < ../dwm-patches.diff
```
If it reports conflicts (e.g., due to upstream changes), edit the files to resolve (usually simple merges), then remove .rej files.

