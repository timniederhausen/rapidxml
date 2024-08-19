# RapidXml

This is a fork of Marcin Kalicinski's RapidXml library.

## Changes

* Fixed some code issues that caused compiling errors with newer compilers.
* Added CMake build scripts.
* Added xml_base::offset() (useful helper for generating diagnostics
  that include the line/column inside the XML file).

## Documentation

The manual can be found at http://timniederhausen.github.io/rapidxml/,
or inside the `gh-pages` branch.

If you want to generate the documentation yourself, run
`doc/documentation/build_docs.bat`.

## License

Please see [license.txt](license.txt).
