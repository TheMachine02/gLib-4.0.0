#ifdef	__gCoreMacroGUARD__
	.error	"gCoreMacro has been already included"
#else
#define	__gCoreMacroGUARD__

; gLib macro, included in CORE
; 'Roswell' revision
#ifndef	gCODENAME
	#define	gCODENAME	Roswell
#endif
#ifndef	gVERSION
	#define	gVERSION	$4000
#endif

#macro __gFetchVertex(gRAMArea)
; 162 TStates, A is clipCode, DE is Z coordinate
; theorical 259.259Kb/s transfer rate
	ld	hl, (gVertexID)
;clipCode
	ld	a, (hl)
	ld	(gRAMArea+$6), a
	inc	h
;vec.x
	ld	e, (hl)
	inc	h
	ld	d, (hl)
	ld	(gRAMArea), de
	inc	h
;vec.y
	ld	e, (hl)
	inc	h
	ld	d, (hl)
	ld	(gRAMArea+$2), de
	inc	h
;vec.z
	ld	e, (hl)
	inc	h
	ld	d, (hl)
	ld	(gRAMArea+$4), de
#endmacro

#macro gRawFetchRaster()
; 22 TStates, HL is the vertexID
; return: DE is the fetched coordinate
; raw write/read 22 TStates
; theorical 545.454Kb/s transfer rate
;point.x
	ld	d, (hl)
	inc	h
;point.y
	ld	e, (hl)
	dec	h
#endmacro
#define gRawFetchRaster gRawFetchRaster()

#macro gFetchRaster()
; 39 TStates, L is vertexID
; return: A point.y, HL fetched coordinate
; raw write/read 22 TStates
; theorical 307.692Kb/s transfer rate
; SMC would speed up this
	ld	a, (gL1Cache)
	ld	h, a
;point.x
	ld	a, (hl)
	inc	h
;point.y
	ld	l, (hl)
	ld	h, a
#endmacro
; 42, 285,714Kb/s
; ld hl, (gVertexID)
; dec h
; ld a, (hl)
; dec h
; ld l, (hl)
; ld h, a

#define gFetchRaster gFetchRaster()


#macro __gCacheVertex(gRAMArea)
; 162 TStates
; theorical 259.259Kb/s transfer rate
	ld	hl, (gVertexID)
;clipCode
	ld	a, (gRAMArea+$6)
	ld	(hl), a
	inc	h
;vec.x
	ld	de, (gRAMArea)
	ld	(hl), e
	inc	h
	ld	(hl), d
	inc	h
;vec.y
	ld	de, (gRAMArea+$2)
	ld	(hl), e
	inc	h
	ld	(hl), d
	inc	h
;vec.z
	ld	de, (gRAMArea+$4)
	ld	(hl), e
	inc	h
	ld	(hl), d
#endmacro

#macro gRightPxlMask
; 16 TStates, B is pxl position
; return: A is the mask to be drawn on screen
; get mask according to pxl position in B, with left-filling convention
	ld	a, b
	cpl
	inc	a
	rla
#endmacro

#macro gLeftPxlMask
; 12 TStates, C is pxl position
; return: A is the mask to be drawn on screen
; get mask according to pxl position in C, with left-filling convention
	ld	a, c
	dec	a
	or	b
#endmacro

; axiom macro (allow multiple file and no ugly definition)
#macro	AXM_LABEL()
	#define	gSubVal	eval(gSubVal+1)
	gSubVal
#endmacro
#define	AXM_LABEL AXM_LABEL()

#macro	AXM_INIT()
	#define	gSubVal	$3F60
	gSubVal
#endmacro
#define	AXM_INIT AXM_INIT()

; extend reg a macro
#define	exda		ld l,a \ rlca \ sbc a,a \ ld h,a

; matrix multiplication macro
#macro	gMultBlock(x,y)
	ld	a, (gWorldViewMatrix+x)
	add	a, a
#if	p0==z
	jp	z, $+12
#else
	jr	z, $+11
#endif
	ld	bc, (y*2+gScratchRAM)
	call	_gMulEntry
	add	hl, de
	ex	de, hl
#endmacro

#define	GNO_LOAD	0
#define	GEX_LOAD	1

#macro	gMultBlockEx(x,y,flag)
#if	flag==GEX_LOAD
	ld	bc, (y*2+gScratchRAM)
#endif
	ld	a, (gWorldViewMatrix+x)
	add	a, a
#if	p0==z
	jp	z, $+8
#else
	jr	z, $+7
#endif
	call	_gMulEntry
	add	hl, de
	ex	de, hl
#endmacro

; predict macro (allow modify jump from some other macro)
#macro	_predict(flag)
	#define	p0 eval(flag)
#endmacro
#define	pred _predict(

#endif