.nolist
#include	"ti83plus.inc"
#include	"Axe.inc"
.list

#ifndef	gCODENAME
	#define	gCODENAME	Roswell
#endif
#ifndef	gVERSION
	#define	gVERSION	$4000
#endif

#ifndef	gCOMPILE_ASM
	#define	gCOMPILE_AXM
#endif

#define 	z 	$00
#define 	nz 	$FF
#define	p0	nz
#define	gNO_LOAD	0
#define	gEX_LOAD	1

;Errors
#define	gOUT_OF_MEMORY	$FFFF
#define	gSTACK_FULL	$DFFF
#define	gUNKNOWN		$CFFF

#define	gFLAGS		asm_Flag2

#define	gMODELVIEW		gMatrix
#define	gCACHE_SIZE	2560		;1792(L2)512(L1)256(Bound)
#define	gVERTEX_CACHE_SIZE	1792
#define	gRASTER_CACHE_SIZE	512

#define	gVAO_SIZE		20

; code bit
#define	gP0Bit	7	; z=0 plane
#define	gP1Bit	6
#define	gP2Bit	5
#define	gP3Bit	4
#define	gP4Bit	3
#define	gUndef	2
#define	gCodeBit	1	;z:code calculated,nz:todo
#define	gPDivBit	0	;z:projected,nz:todo

; mask
#define	gP0Mask	%10000000
#define	gP1Mask	%01000000
#define	gP2Mask	%00100000
#define	gP3Mask	%00010000
#define	gP4Mask	%00001000
#define	gCodeMask	%00000010
#define	gPDivMask	%00000001

; variable defines
; 256 bytes LUT CST
#define	gSinLUT		saveSScreen + 276
; 128 bytes pixel shader area - 192 bytes
#define	gFillLUT		saveSScreen + 532
; 15 bytes
#define	gMatrix		saveSScreen + 660
; 2 bytes
#define	gError		saveSScreen + 675
; 2 bytes
#define	gVertexID		saveSScreen + 677
#define	gL2Cache		saveSScreen + 678
#define	gL1Cache		saveSScreen + 679
; 2 bytes
#define	gVertexCache	saveSScreen + 680
; shaders things
#define	gLayer		saveSScreen + 682
#define	gQualifier0	saveSScreen + 684
#define	gFreeRAM		saveSScreen + 686

#define	gVertexArrayName	saveSScreen + 760
#define	gVertexArrayID	saveSScreen + 765

; OP1-6 define (tmp RAM memory)
#define	gScratchRAM	$848F

#define	gPosition		$8478
#define	gPositionX		$8478
#define	gPositionY		$847A
#define	gPositionZ		$847C
#define	gClipCode		$847E

; vertex
#define	gVertex		$8480
#define	gVertexX		$8480
#define	gVertexY		$8482
#define	gVertexZ		$8484
#define	gColor		$8486

; classical vertex attribute
#define	gNormal		$8488
#define	gNormalX		$8488
#define	gNormalY		$8489
#define	gNormalZ		$848A

#define	gTexCoord		$848B
#define	gTexCoordS		$848B
#define	gTexCoordT		$848C

#define	gRasterX		$848D
#define	gRasterY		$848E

; triangle filling variables
#define	gDeltaYLeft	$8478
#define	gDeltaXLeft	$8479
#define	gDeltaYRight	$847A
#define	gDeltaXRight	$847B
#define	gErrorLeft		$847C
#define	gErrorRight	$847D
#define	gL6RowBase		$847E
#define	gDefaultReg	$8480

; cliping vertex data
#define	gClipCoordX1	$8478
#define	gClipCoordY1	$847A
#define	gClipCoordZ1	$847C
#define	gClipCoordX2	$847E
#define	gClipCoordY2	$8480
#define	gClipCoordZ2	$8482

; line coordinate
#define	gLineX0		$8478
#define	gLineY0		$8479
#define	gLineX1		$847A
#define	gLineY1		$847B
