# Digital Image Processing Systems — MATLAB Project

A MATLAB GUI application for digital image processing, developed as a university project for the *Digital Image Processing Systems* course at ETF.

## What it does

- Loads images through a file-picker interface
- Applies **Gabor filters** for texture analysis and feature extraction
- Performs **morphological image operations**: erosion, dilation, opening, closing
- Organises functionality across multiple GUI windows for clean navigation

## Application modules

| Script | Purpose |
|--------|---------|
| `Pocetak.m` | Main entry window — file loading and navigation to processing modules |
| `Gabor.m` / `Gaborverzija.m` | Gabor filter application and parameter controls |
| `Morfoloskeoperacije.m` | Morphological operations: erosion, dilation, opening, closing |
| `projekatmorf.m` | Combined morphological project implementation |

## Key concepts demonstrated

| Concept | Detail |
|---------|--------|
| MATLAB GUI (GUIDE) | Multi-window graphical interface with button callbacks and image display axes |
| Gabor filtering | Frequency- and orientation-selective linear filter for texture analysis |
| Morphological operations | Structuring-element-based binary/grayscale image transformations |
| Image I/O | Loading, displaying, and processing images inside MATLAB figures |
| Modular GUI design | Each processing technique lives in its own `.m` GUI script |

## Running

Open MATLAB, navigate to the project directory, and run:

```matlab
Pocetak
```

Requires the **Image Processing Toolbox**.
