.nolist
#include	"ti83plus.inc"
#include	"Axe.inc"
.list

#define	gCOMPILE_AXM

#ifndef	gCODENAME
	#define	gCODENAME	Roswell
#endif
#ifndef	gVERSION
	#define	gVERSION	$4000
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
#define	gPRIMITIVE_CULLED	$0000
#define	gPRIMITIVE_PASSED	$0001
#define	gPRIMITIVE_CLIPPED	$0002
#define	gNOCLIPCODE		%11000000

#define	gFLAGS		asm_Flag2

#define	gCACHE_SIZE	2560		;1792(L2)512(L1)256(Bound)
#define	gVERTEX_CACHE_SIZE	1792
#define	gRASTER_CACHE_SIZE	512

#define	gVAO_SIZE		20

; code bit
#define	gP0Bit	0	; z=0 plane
#define	gP1Bit	1
#define	gP2Bit	2
#define	gP3Bit	3
#define	gP4Bit	4
#define	gUndef	5
#define	gPDivBit	6	;z:projected,nz:todo
#define	gCodeBit	7	;z:code calculated,nz:todo

; mask
#define	gP0Mask	%00000001
#define	gP1Mask	%00000010
#define	gP2Mask	%00000100
#define	gP3Mask	%00001000
#define	gP4Mask	%00010000
#define	gPDivMask	%01000000
#define	gCodeMask	%10000000

#define	dwait	 in a,($10) \ and %10010000 \ jr nz, $-4 

; variable defines
; 256 bytes LUT CST
;#define	gSinLUT		saveSScreen + 276
#define	gSinLUT		$8000
; 128 bytes pixel shader area - 192 bytes
#define	gFillLUT		saveSScreen + 532
; 15 bytes
#define	gWorldViewMatrix	saveSScreen + 660
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
#define	gFreeRAM		saveSScreen + 684

#define	gVertexArrayName	saveSScreen + 760
#define	gVertexArrayID	saveSScreen + 765

; OP1-6 define (tmp RAM memory)

#define	gClipCode		$8478
#define	gPosition		$8479
#define	gPositionX		$8479
#define	gPositionY		$847B
#define	gPositionZ		$847D

; vertex
#define	gColor		$8480
#define	gVertex		$8481
#define	gVertexX		$8481
#define	gVertexY		$8483
#define	gVertexZ		$8485

; cliping vertex data
#define	gClipCoordX1	$8480
#define	gClipCoordY1	$8482
#define	gClipCoordZ1	$8484
#define	gClipCoordX2	$8486
#define	gClipCoordY2	$8488
#define	gClipCoordZ2	$848A

; classical vertex attribute
#define	gNormal		$8488
#define	gNormalX		$8488
#define	gNormalY		$8489
#define	gNormalZ		$848A

#define	gTexCoord		$848B
#define	gTexCoordS		$848B
#define	gTexCoordT		$848C

#define	gScratchRAM	$848D

#define	gLRPFactor1	$848D
#define	gLRPFactor2	$848E
#define	gClipVertexID	$848F
#define	gClipVertexID1	$848F
#define	gClipVertexID2	$8490

; line coordinate
#define	gLineX0		saveSScreen+4
#define	gLineY0		saveSScreen+5
#define	gLineX1		saveSScreen+6
#define	gLineY1		saveSScreen+7

#define	gPoint1		saveSScreen + 8
#define	gPointX1		saveSScreen + 8
#define	gPointY1		saveSScreen + 9

#define	gPoint2		saveSScreen + 10
#define	gPointX2		saveSScreen + 10
#define	gPointY2		saveSScreen + 11

#define	gPoint3		saveSScreen + 12
#define	gPointX3		saveSScreen + 12
#define	gPointY3		saveSScreen + 13

#define	gXGrad1		saveSScreen + 14
#define	gXGrad1HSB		saveSScreen + 15
#define	gXGrad2		saveSScreen + 16
#define	gXGrad2HSB		saveSScreen + 17

#define	gXDelta1		saveSScreen + 18
#define	gXDelta2		saveSScreen + 20

#define	gCurrentY		saveSScreen + 22

#define	gVertexStream	saveSScreen
#define	gCountStream		saveSScreen + 2
