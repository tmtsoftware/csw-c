# Change Log
All notable changes to this project will be documented in this file.

## [csw-c v4.0.4] - 2022-

### Changed

- Updated Units to match latest CSW snapshot

## [csw-c v4.0.3] - 2022-02-14

### Changed

- Updated for csw-4.0.1

## [csw-c v4.0.2] - 2021-11-22

### Changed

- Minor changes to build environment
- Tested on MacOS-12

### Added

- Add install.sh script that makes a binary release with native dependencies

## [csw-c v4.0.1] - 2021-09-27

### Changed

- Updated CSW version to 4.0.0
- 
### Added

- Added tai and utc units for time values

- Added a dependency on the [zlog](https://github.com/HardySimpson/zlog) logging library and replaced printf() with log messages
  Note that your application's main() must initialize the zlog library at startup.
  See the [zlog API](https://hardysimpson.github.io/zlog/UsersGuide-EN.html#sec:dzlog-API) for details.

## [csw-c v4.0.0] - 2021-08-24

### Changed

- Updated CSW version to 4.0.0-RC1

- Removed CSW Struct parameter type 

- Shared libcsw.so.1 is installed (was previously static libcsw.a)

- Changed type of units argument for a CSW Parameter to an Enum matching the CSW unit values

- Added support for UTCTime and TAITime parameters

- Added tests for String and Choice (enum) type parameters

## [csw-c v3.0.1] - 2021-02-12

### Changed

- Updated test version to CSW-3.0.1

## [csw-c v3.0.0-RC1] - 2020-12-01

### Changed

- Updated test version to CSW-3.0.0-RC1

## [csw-c v3.0.0-M1] - 2020-09-29

### Changed

- Updated for latest csw version (v3.0.0-M1)

## [tmtpycsw v2.0.0] - 2020-03-03

### Changed

- Updated for csw-2.0.0
