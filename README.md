test-bench
==========

ORCC/Papify tests on one and more cores to assess coherent functionality and results

##Test 1:
Two actors/two actions papified, everything in the same core.

####Papify and mapping settings
| Actor          | Action       | Events       | Mapping      |
| :------------- | :----------- | :----------- |:-----------: |
|DecodingPictureBuffer  |getPix             |PAPI_TOT_INS |c0|
|                       |isNewSlice         |PAPI_TOT_INS |c0|
|InterPrediction        |getWeightDenom.skip|PAPI_TOT_INS |c0|
|                       |getAllSamples.done |PAPI_TOT_INS |c0|

####Runs
|         |              |
| :------ | :----------- |
|Hardware |[gdem8](sys_info/gdem8)|
|Sequence |[BQSquare_416x240_60_qp27.bin](HEVC Sequences/BQSquare_416x240_60_qp27.bin)|
|XCF      |[test1/Top_mpegh_part2_main.xcf](test1/Top_mpegh_part2_main.xcf)|
|Date     ||
|Rsults   ||


##Test 2
Two actors/two actions papified, one in each core.

####Papify and mapping settings
| Actor          | Action       | Events       | Mapping      |
| :------------- | :----------- | :----------- |:-----------: |
|DecodingPictureBuffer  |getPix             |PAPI_TOT_INS |c0|
|                       |isNewSlice         |PAPI_TOT_INS |c0|
|InterPrediction        |getWeightDenom.skip|PAPI_TOT_INS |c1|
|                       |getAllSamples.done |PAPI_TOT_INS |c1|

####Runs
|                |              |
| :------------- | :----------- |
|Hardware |[gdem8](sys_info/gdem8)|
|Sequence |[BQSquare_416x240_60_qp27.bin](HEVC Sequences/BQSquare_416x240_60_qp27.bin)|
|XCF      |[test2/Top_mpegh_part2_main.xcf](test2/Top_mpegh_part2_main.xcf)|
|Date     ||
|Rsults   ||
