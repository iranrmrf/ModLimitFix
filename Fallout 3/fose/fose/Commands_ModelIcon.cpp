#include "Commands_ModelIcon.h"

#include "GameAPI.h"
#include "GameForms.h"
#include "GameObjects.h"
#include "GameRTTI.h"

enum EMode
{
	kGet = 0,
	kSet,
	kMod,
	kCompare,
	kCopy
}; 

enum {
	kVal_Model,
	kVal_Icon,

	kVal_BipedMale,
	kVal_BipedFemale,
	kVal_GroundMale,
	kVal_GroundFemale,
	kVal_IconMale,
	kVal_IconFemale,
};

static String* PathStringFromForm(TESForm* form, UInt32 whichValue, EMode mode)
{
	switch(whichValue) {
		case kVal_Model:
		{
			TESModel* model = DYNAMIC_CAST(form, TESForm, TESModel);
			if (model) {
				return &model->nifPath;
			}
			break;
		}
		case kVal_Icon:
		{
			TESIcon* icon = DYNAMIC_CAST(form, TESForm, TESIcon);
			if (icon) {
				return &icon->ddsPath;
			}
			break;
		}

		case kVal_BipedMale:
		case kVal_BipedFemale:
		{
			TESBipedModelForm* biped = DYNAMIC_CAST(form, TESForm, TESBipedModelForm);
			if (biped) {
				TESModel& model = biped->bipedModel[whichValue - kVal_BipedMale];
				return &model.nifPath;
			}
			break;
		}
		
		case kVal_GroundMale:
		case kVal_GroundFemale:
		{
			TESBipedModelForm* biped = DYNAMIC_CAST(form, TESForm, TESBipedModelForm);
			if (biped) {
				TESModel& model = biped->groundModel[whichValue - kVal_GroundMale];
				return &(model.nifPath);
			}
			break;
		}


		case kVal_IconMale:
		case kVal_IconFemale:
		{
			TESBipedModelForm* biped = DYNAMIC_CAST(form, TESForm, TESBipedModelForm);
			if (biped) {
				TESIcon& icon = biped->icon[whichValue - kVal_IconMale];
				return &icon.ddsPath;
			}
			break;
		}
	}
	return NULL;
}

static bool PathFunc_Execute(COMMAND_ARGS, UInt32 whichValue, EMode mode)
{
	*result = 0;
	
	TESForm* targetForm = NULL;
	TESForm* srcForm = NULL;
	char textArg[256] = { 0 };

	bool bExtracted = false;
	if (mode == kCopy) {
		bExtracted = ExtractArgsEx(EXTRACT_ARGS_EX, &srcForm, &targetForm);
		if (!srcForm) return true;
	} else if (mode == kGet) {
		bExtracted = ExtractArgsEx(EXTRACT_ARGS_EX, &targetForm);
	}
	else {
		bExtracted = ExtractArgsEx(EXTRACT_ARGS_EX, &textArg, &targetForm);
		if (textArg[0] == '\0') return true;
	}

	srcForm = srcForm->TryGetREFRParent();
	targetForm = targetForm->TryGetREFRParent(); 
	if (!targetForm) {
		if (!thisObj) return true;
		targetForm = thisObj->baseForm;
	}

	String* theString = PathStringFromForm(targetForm, whichValue, mode);
	if (theString != NULL) {
		switch(mode) {
			case kSet:
				{
					theString->Set(textArg);
					break;
				}
			case kMod:
				{
					// we expect textArg to be in the following format: "toReplace|replaceWith"
					std::string strTextArg(textArg);
					// look and see if the input has the pipe character
					std::string::size_type pipePos = strTextArg.find('@');
					if (pipePos != std::string::npos) {
						// we found the pipe
						// now look for the replacement string
						std::string toReplace(strTextArg.substr(0, pipePos));
						theString->Replace(toReplace.c_str(), &strTextArg[pipePos+1]);
					}
					break;
				}

			case kCompare:
				{
					bool bFound = theString->Includes(textArg);
					*result = bFound ? 1 : 0;
					break;
				}
			case kCopy:
				{
					String* srcString = PathStringFromForm(srcForm, whichValue, mode);
					if (srcString) {
						theString->Set(srcString->m_data);
					}
					break;
				}

			// Get not supported until FileFinder exposed
#if 0
			case kGet:
				{
					std::string sFilePath;
					if (whichValue == kVal_Icon)
						sFilePath = std::string("data\\textures\\menus\\icons\\") + std::string(theString->m_data);
					else
						sFilePath = std::string("data\\meshes\\") + std::string(theString->m_data);

					*result = (*g_FileFinder)->FindFile(sFilePath.c_str(), 0, 0, -1) ? 1 : 0;

					break;
				}
#endif

			default:
				break;
		}
	}
	return true;
}

/******************************
	commands
******************************/

bool Cmd_ModelPathIncludes_Execute(COMMAND_ARGS)
{
	return PathFunc_Execute(PASS_COMMAND_ARGS, kVal_Model, kCompare);
}
