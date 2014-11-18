test-bench
==========

ORCC/Papify tests on one and more cores to assess coherent functionality and results


####test 1
Hardware: [gdem8](sys_info/gdem8)

Sequence: [BQSquare_416x240_60_qp27.bin](HEVC Sequences/BQSquare_416x240_60_qp27.bin)

| Actor | Action         | Events | Core |
| :------------- | :----------- | :----------- |:-----------: |
| DecodingPictureBuffer      |getPix|PAPI_TOT_INS|0|
|     |isNewSlice|PAPI_TOT_INS|0|
| InterPrediction      |getWeightDenom.skip|PAPI_TOT_INS|0|
|     |getAllSamples.done|PAPI_TOT_INS|0|

Date:

Results

####test 1
Hardware: [gdem8](sys_info/gdem8)

Sequence: [BQSquare_416x240_60_qp27.bin](HEVC Sequences/BQSquare_416x240_60_qp27.bin)

| Actor | Action         | Events | Core |
| :------------- | :----------- | :----------- |:-----------: |
| DecodingPictureBuffer      |getPix|PAPI_TOT_INS|0|
|     |isNewSlice|PAPI_TOT_INS|0|
| InterPrediction      |getWeightDenom.skip|PAPI_TOT_INS|0|
|     |getAllSamples.done|PAPI_TOT_INS|0|

[XDF](test1/Top_mpegh_part2_main.xcf)

Date:

Results

####test 2
Hardware: [gdem8](sys_info/gdem8)

Sequence: [BQSquare_416x240_60_qp27.bin](HEVC Sequences/BQSquare_416x240_60_qp27.bin)

| Actor | Action         | Events | Core |
| :------------- | :----------- | :----------- |:-----------: |
| DecodingPictureBuffer      |getPix|PAPI_TOT_INS|0|
|     |isNewSlice|PAPI_TOT_INS|0|
| InterPrediction      |getWeightDenom.skip|PAPI_TOT_INS|1|
|     |getAllSamples.done|PAPI_TOT_INS|1|

[XDF](test2/Top_mpegh_part2_main.xcf)

Date:

Results
