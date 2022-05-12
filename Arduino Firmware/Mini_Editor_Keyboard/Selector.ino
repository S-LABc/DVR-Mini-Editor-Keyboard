/** 
 * Инструменты назначаются на любую клавишу, в количестве (кроме клавиш ручки поиска).
 * Число в case это номер инструмента. Задается в ToolsNumber в modes.h.
 * Входящие значение tool_ берётся из массива tool_number. В массив оно попадает из EEPROM.
 * Значение может быть 0-65535 (2 байта, 16 бит).
*/
void toolSelection (uint8_t tool_) {
  switch (tool_) {
    case TOOL_NONE:                            // 0
      toolNone();
    break;
    case TOOL_UNDO:
      toolUndo();
    break;
    case TOOL_SNAPPING:
      toolSnapping();
    break;
    case TOOL_CINEMA_VIEWER:
      toolCinemaViewer();
    break;
    case TOOL_INSERT:
      toolInsert();
    break;
    case TOOL_APPEND_TO_END_OF_TIMELINE:       // 5
      toolAppendToEndOfTimeline();
    break;
    case TOOL_RIPPLE_OVERWRITE:
      toolRippleOverwrite();
    break;
    case TOOL_FIT_TO_FILL:
      toolFitToFill();
    break;
    case TOOL_PLACE_ON_TOP:
      toolPlaceOnTop();
    break;
    case TOOL_REPLACE:
      toolReplace();
    break;
    case TOOL_MARK_IN:                         // 10
      toolMarkIn();
    break;
    case TOOL_ADD_MARKER:
      toolAddMarker();
    break;
    case TOOL_MARK_OUT:
      toolMarkOut();
    break;
    case TOOL_RESIZE_IN:
      toolResizeIn();
    break;
    case TOOL_RESIZE_OUT:
      toolResizeOut();
    break;
    case TOOL_ROLL:                            // 15
      toolRoll();
    break;
    case TOOL_MOVE:
      toolMove();
    break;
    case TOOL_SLIDE:
      toolSlide();
    break;
    case TOOL_SLIP:
      toolSlip();
    break;
    case TOOL_SOURCE_TIMELINE_VIEWER:
      toolSourceTimelineViewer();
    break;
    case TOOL_PROJECT_SETTINGS:                // 20
      toolProjectSettings();
    break;
    case TOOL_SOURCE_CLIP_TAPE:
      toolSourceClipTape();
    break;
    case TOOL_WHEEL_SHUTTLE:
      toolWheelShuttle();
    break;
    case TOOL_WHEEL_JOG:
      toolWheelJog();
    break;
    case TOOL_WHEEL_SCROLL:
      toolWheelScroll();
    break;
    case TOOL_PAUSE_START_PLAYBACK:            // 25
      toolPauseStartPlayback();
    break;
    case TOOL_PLAY_REVERS:
      toolPlayRevers();
    break;
    case TOOL_PLAY_FORWARD:
      toolPlayForward();
    break;
    case TOOL_GO_TO_IN:
      toolGoToIn();
    break;
    case TOOL_GO_TO_OUT:
      toolGoToOut();
    break;
    case TOOL_RIPLE_START_TO_PLAYHEAD:         // 30
      toolRipleStartToPlayhead();
    break;
    case TOOL_RIPLE_END_TO_PLAYHEAD:
      toolRipleEndToPlayhead();
    break;
    case TOOL_PREVIOUS_CLIP_EDIT:
      toolPreviousClipEdit();
    break;
    case TOOL_NEXT_CLIP_EDIT:
      toolNextClipEdit();
    break;
    case TOOL_FAST_REVERSE:
      toolFastReverse();
    break;
    case TOOL_FAST_FORWARD:                    // 35
      toolFastForward();
    break;
    case TOOL_FRAME_REVERSE:
      toolFrameReverse();
    break;
    case TOOL_FRAME_FORWARD:
      toolFrameForward();
    break;
    case TOOL_ONE_FRAME_LEFT:
      toolOneFrameLeft();
    break;
    case TOOL_ONE_FRAME_RIGHT:
      toolOneFrameRight();
    break;
    case TOOL_TIMELINE_START:                  // 40
      toolTimelineStart();
    break;
    case TOOL_TIMELINE_END:
      toolTimelineEnd();
    break;
    case TOOL_MULTIFRAME_LEFT:
      toolMultiframeLeft();
    break;
    case TOOL_MULTIFRAME_RIGHT:
      toolMultiframeRight();
    break;
    case TOOL_ONE_SECOND_REVERSE:
      toolSecondReverse();
    break;
    case TOOL_ONE_SECOND_FORWARD:              // 45
      toolSecondForward();
    break;
    case TOOL_CHANGE_CLIP_SPEED:
      toolChangeClipSpeed();
    break;
    case TOOL_CHANGE_CLIP_DURATION:
      toolChangeClipDuration();
    break;
    case TOOL_SHOW_CURVE_EDITOR:
      toolShowCurveEditor();
    break;
    case TOOL_SHOW_KEYFRAME_EDITOR:
      toolShowKeyframeEditor();
    break;
    case TOOL_SELECT_NEAREST_VIDEO_EDIT_PIONT: // 50
      toolSelectNearestVideoEditPoint();
    break;
    case TOOL_SELECT_NEAREST_AUDIO_EDIT_PIONT:
      toolSelectNearestAudioEditPoint();
    break;
    case TOOL_DECREASE_AUDIO_LEVEL_1DB:
      toolDecreaseAudioLevel1dB();
    break;
    case TOOL_INCREASE_AUDIO_LEVEL_1DB:
      toolIncreaseAudioLevel1dB();
    break;
    case TOOL_MARK_CLIP:
      toolMarkClip();
    break;
    case TOOL_CLEAR_IN:                        // 55
      toolClearIn();
    break;
    case TOOL_CLEAR_OUT:
      toolClearOut();
    break;
    case TOOL_CLEAR_IN_AND_OUT:
      toolClearInAndOut();
    break;
    case TOOL_ADD_TRANSITION:
      toolAddTransition();
    break;
    case TOOL_ADD_VIDEO_ONLY_TRANSITION:
      toolAddVideoOnlyTransition();
    break;
    case TOOL_ADD_AUDIO_ONLY_TRANSITION:       // 60
      toolAddAudioOnlyTransition();
    break;
    case TOOL_SELECT_NEAREST_CLIP_GAP:
      toolSelectNearestClipGap();
    break;
    case TOOL_SELECT_NEAREST_EDIT_POINT:
      toolSelectNearestEditPoint();
    break;
    case TOOL_PROJECT_MANAGER:
      toolProjectManager();
    break;
    case TOOL_SWITCH_TO_PAGE_MEDIA:
      toolSwitchToPageMedia();
    break;
    case TOOL_SWITCH_TO_PAGE_CUT:              // 65
      toolSwitchToPageCut();
    break;
    case TOOL_SWITCH_TO_PAGE_EDIT:
      toolSwitchToPageEdit();
    break;
    case TOOL_SWITCH_TO_PAGE_FUSION:
      toolSwitchToPageFusion();
    break;
    case TOOL_SWITCH_TO_PAGE_COLOR:
      toolSwitchToPageColor();
    break;
    case TOOL_SWITCH_TO_PAGE_FAIRLIGHT:
      toolSwitchToPageFairlight();
    break;
    case TOOL_SWITCH_TO_PAGE_DELIVER:          // 70
      toolSwitchToPageDeliver();
    break;
    case TOOL_CUT_TO_ANGLE_1:
      toolCutToAngle1();
    break;
    case TOOL_CUT_TO_ANGLE_2:
      toolCutToAngle2();
    break;
    case TOOL_CUT_TO_ANGLE_3:
      toolCutToAngle3();
    break;
    case TOOL_CUT_TO_ANGLE_4:
      toolCutToAngle4();
    break;
    case TOOL_CUT_TO_ANGLE_5:                  // 75
      toolCutToAngle5();
    break;
    case TOOL_CUT_TO_ANGLE_6:
      toolCutToAngle6();
    break;
    case TOOL_CUT_TO_ANGLE_7:
      toolCutToAngle7();
    break;
    case TOOL_CUT_TO_ANGLE_8:
      toolCutToAngle8();
    break;
    case TOOL_CUT_TO_ANGLE_9:
      toolCutToAngle9();
    break;
    case TOOL_SAVE_PROJECT:                   // 80
      toolSaveProject();
    break;
    case TOOL_SAVE_PROJECT_AS:
      toolSaveProjectAs();
    break;
    case TOOL_SWAP_CLIPS_TOWARDS_LEFT:
      toolSwapClipsTowardsLeft();
    break;
    case TOOL_SWAP_CLIPS_TOWARDS_RIGHT:
      toolSwapClipsTowardsRight();
    break;
    case TOOL_SELECT_ALL:
      toolSelectAll();
    break;
    case TOOL_DESELECT_ALL:                  // 85
      toolDeselectAll();
    break;
    case TOOL_REDO:
      toolRedo();
    break;
    case TOOL_DELETE_MARKER:
      toolDeleteMarker();
    break;
    case TOOL_RIPPLE_DELETE:
      toolRippleDelete();
    break;
    case TOOL_OVERWRITE:
      toolOverwrite();
    break;
    case TOOL_SPLIT_CLIP:                    // 90
      toolSplitClip();
    break;
    case TOOL_DELETE_GAPS:
      toolDeleteGaps();
    break;
    case TOOL_STOP:
      toolStop();
    break;
    case TOOL_PLAY_SLOW:
      toolPlaySlow();
    break;
    case TOOL_COPY:
      toolCopy();
    break;
    case TOOL_CUT:                           // 95
      toolCut();
    break;
    case TOOL_PASTE:
      toolPaste();
    break;
    case TOOL_ENABLE_CLIP:
      toolEnableClip();
    break;
    case TOOL_PREFERENCES:
      toolPreferences();
    break;
    case TOOL_LOOP_UNLOOP:
      toolLoopUnloop();
    break;
    case TOOL_FREEZE_FRAME:                  // 100
      toolFreezeFrame();
    break;
    case TOOL_CHANGE_AUDIO_LEVEL:
      toolChangeAudioLevel();
    break;
    case TOOL_SWAP_CLIPS:
      toolSwapClips();
    break;
    case TOOL_LINKED_SELECTION:
      toolLinkedSelection();
    break;
    case TOOL_KEYBOARD_CUSTOMIZATION:
      toolKeyboardCustomization();
    break;
    case TOOL_QUIT_DAVINCI_RESOLVE:          // 105
      toolQuitDaVinciResolve();
    break;
    case TOOL_NEW_TIMELINE:
      toolNewTimeline();
    break;
    case TOOL_INPORT_MEDIA:
      toolImportMedia();
    break;
    case TOOL_SYNC_BIN:
      toolSyncBin();
    break;
    default: // Если что-то пошло не так
      toolNone();
    break;
  }
}
