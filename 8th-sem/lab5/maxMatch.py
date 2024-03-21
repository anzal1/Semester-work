from nltk.corpus import words

inputString = "Thequickbrownfoxjumpsoverthelazydogwhilstdancingunderneaththeglitteringmoonlightandwhisperingsecretsintothewindasshadowslurkbehindtreesandstarlightsparkleslikejewelsinthenightskyfillingthesoulwithawondroussenseofmysteryandadventureastimeflowssilentlythroughtheuniversewithallitsmajestyandwonderrevealingthedeepertruthsoflifeandexistenceintheeverexpandingtapestryofcreationwhereeverymomentisanewbeginningandanendlesspossibilityawaitingdiscoveryandexplorationbeneaththesurfaceofconsciousnessandintheheartofthesoulwheretheessenceofbeingresidesinharmonywiththeunfoldingcosmicdancethatbindsusalltogetherinasacredweboflifeandloveconnectinguswiththevastnessoftheinfiniteandtheeternalflowoftheuniverseinitsendlesscycleofbirthdeathandrebirthagainandagaininaperpetualrhythmofcreationandtransformationforeverunfoldingandevolvingintheeternalnowofeternitywithoutbeginningorendjustasimplythesongofexistenceechoingthroughtheemptyspaceoftimeandspace"
inputString = inputString.lower()
tokens = []
lowercaseCorpus = set(words.words())   
i = 0
while i < len(inputString):
    maxWord = ""
    for j in range(i, len(inputString)):
        tempWord = inputString[i:j+1]
        if tempWord in lowercaseCorpus and len(tempWord) > len(maxWord):
            maxWord = tempWord
    i = i + len(maxWord)
    tokens.append(maxWord)

print(tokens)