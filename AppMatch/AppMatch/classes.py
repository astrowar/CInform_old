classes = ["BlockEnums","BlockKind","Unresolved","BlockKindOf","BlockKindAction","BlockKindValue","BlockListOfKind","BlockNamedValue","BlockVariable","BlockInstanceVariable","BlockList","BlockEnums","BlockProperty","BlockAssertion_isDefaultAssign","BlockNoum","BlockKind_InstanceVariable","BlockAssertion_isDirectAssign","BlockAssertion_canBe","BlockAssertion_is","BlockIsVerb","BlockAssertion_isActionOf","BlockIsNotVerb","BlockMatchAny","BlockMatchNamed","BlockMatchList","BlockMatchDirectIsNot","BlockMatchKind","BlockMatchProperty","BlockMatchBlock","BlockMatchOR","BlockMatchAND","BlockMatchDirectIs","BlockMatchIsVerb","BlockMatchIsNotVerb","BlockAssertion_isNotDirectAssign","BlockMatchNoum","BlockBooleanAND","BlockVerb","BlockBooleanOR","BlockBooleanNOT","BlockSelector_All","BlockSelector_Any","BlockStaticDispatch","BlockAction","BlockActionCall","VariableNamed","BlockUnderstandDynamic","BlockUnderstandStatic","BlockToDecideWhether","BlockToDecideIf","BlockToDecideWhat_FirstNoum","BlockToDecideWhat","BlockToDecideOn","BlockActionApply","BlockKindOfName","BlockArgumentInput","BlockText","BlockInstance","BlockSimetricRelation","BlockASimetricRelation","BlockRelationInstance","BlockVerbRelation","BlockAssertion_isConstantAssign","BlockAssertion_isForbiddenAssign","BlockAssertion_isVariable","BlockAssertion_isNamedValueOf","BlockAssertion_InstanceVariable","BlockAssertion_isInstanceOf","BlockDinamicDispatch","BlockNow"]

useShared = True 

if (useShared ==False):

    if(False):
      for c in classes:
        print "C"+c+"* asC"+c+"(CBlock* c )\n{ \n   if ( c->type() == BlockType::"+c+")\n        return static_cast<C"+c+"*>(c);\n   return nullptr;\n} "
    else:  
       for c in classes:
          print "C"+c+"* asC"+c+"(CBlock* c ); "

else:
    if(True):
      for c in classes:
          print "H"+c+" asH"+c+"(HBlock c )\n{ \n   if (c != nullptr && c->type() == BlockType::"+c+")\n        return static_pointer_cast<C"+c+">(c);\n   return nullptr;\n} "
    else:  
       for c in classes:
          print "H"+c+" asH"+c+"(HBlock* c ); "
      