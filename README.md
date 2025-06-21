# SotfP
Simple otf Parser

Parses OTF font formats into segmented instructions mapped with relevant numerical data.

This project is largely designed to showcase a simple implementation of OTF font file parsing.
That being said, this is a functional parser that I will be implementing into my custom 3D Graphics Framework ([lbgfx](https://github.com/NicholasTranquilli/lbgfx))

While this is functional, many shortcuts were taken to decrease development time and produce something simple and easy to understand.

From my testing, any font downloaded from [Glyphr Studio](https://www.glyphrstudio.com/app/) should work with this parser (this also includes any existing OTF fonts that are uploaded and re-downloaded from their glyph editor).

## Support
| Supported?  | OTF Font Feature |
| :-------------: | ------------- |
| :heavy_check_mark:  | CFF tables |
| :heavy_check_mark:  | CMAP tables |
| :warning: | OTF Tables Excluding CFF and CMAP |
| :heavy_check_mark:  | Format 4 CMAP tables |
| :warning: | CFF Charstring Subroutines  |
| :x: | Non-Format 4 CMAP tables |
| :x: | Non-CFF glyph tables |
| :x: | Font Libraries (fonts containing multiple fonts) |
| :heavy_check_mark: | Parsing into 3D vectors and indices for graphics development |

- :heavy_check_mark: Supported
- :warning: Planned Future Development
- :x: Currently Unsupported
- :triangular_flag_on_post: Next item in development

## Credits And Resources
[Adobe CFF Format Spec](https://adobe-type-tools.github.io/font-tech-notes/pdfs/5176.CFF.pdf)

[Adobe Type 2 Charstring Format Spec](https://adobe-type-tools.github.io/font-tech-notes/pdfs/5177.Type2.pdf)

[Adobe Type 1 FontFormat Spec](https://adobe-type-tools.github.io/font-tech-notes/pdfs/T1_SPEC.pdf)

[CFF ‘Font Building’ Article](https://pomax.github.io/CFF-glyphlet-fonts/)

[OTF Format Docs](https://learn.microsoft.com/en-us/typography/opentype/spec/otff)

[Glyphr Studio](https://www.glyphrstudio.com/app/)  (Very useful for building test fonts)


