ScriptName SGBTimer extends ActiveMagicEffect 

Spell Property pAbilityToRemove Auto
Int Property pHoursToWait Auto

Event OnUpdateGameTime()
    ; 	debug.trace(self + "OnUpdateGameTime")
    Game.GetPlayer().RemoveSpell(pAbilityToRemove)
    debug.trace(self + "game update triggered")
EndEvent
    
Event OnEffectStart(Actor akTarget, Actor akCaster)  
        ; start timer
        RegisterForSingleUpdateGameTime(pHourstoWait)
        debug.MessageBox("onEffectStart triggered")
        debug.trace(self + "onEffectStart triggered")
        
EndEvent