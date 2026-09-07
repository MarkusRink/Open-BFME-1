// ?update@DozerActionMoveToActionPosState@@UAE?AW4StateReturnType@@XZ
// partial score=0.9 date=2026-09-07
// Banked near miss for retail RVA 0x002B8100.
// The existing DozerAIUpdate.cpp carries the complete TU reconstruction.
// This excerpt preserves the recovered BFME layout and the candidate body.

class BfmeDozerMoveToActionPosStateAttempt
{
public:
	StateReturnType update();
};

StateReturnType BfmeDozerMoveToActionPosStateAttempt::update()
{
	BfmeDozerMoveStateFields *state = (BfmeDozerMoveStateFields *)this;
	Object *goalObject = ((StateMachine *)state->m_machine)->getGoalObject();
	Object *dozer = state->m_machine->m_owner;
	if (goalObject == 0 || dozer == 0)
		return STATE_FAILURE;

	BfmeDozerMoveAiVTable *ai =
		(BfmeDozerMoveAiVTable *)((BfmeDozerMoveObjectFields *)dozer)->m_ai;
	if (state->m_task == DOZER_TASK_REPAIR && !dozer->isKindOf((KindOfType)15))
	{
		ObjectID currentRepairer = goalObject->getSoleHealingBenefactor();
		if (currentRepairer != INVALID_ID &&
			currentRepairer != ((BfmeDozerMoveObjectFields *)dozer)->m_id)
		{
			BfmeDozerMoveTaskVTable *dozerAI =
				(BfmeDozerMoveTaskVTable *)ai->getDozerAIInterface();
			if (dozerAI != 0)
				dozerAI->internalTaskComplete(state->m_task);
			((BfmeDozerMoveMachineVTable *)state->m_machine)->setGoalObject(0);
			return STATE_FAILURE;
		}
	}

	const Coord3D *goalPos = &state->m_machine->m_goalPosition;
	Real distSqr = ((BfmeGap951 *)dozer)->bfmeGapB951((const BfmePt951 *)goalPos);
	const Real SLOP = 15.0f;
	Real allowableDistanceSqr =
		sqr(max(MIN_ACTION_TOLERANCE,
			((BfmeDozerMoveObjectFields *)dozer)->m_boundingSphereRadius + SLOP));
	if (distSqr <= allowableDistanceSqr)
	{
		if (state->m_task == DOZER_TASK_BUILD)
		{
			((BfmeDozerMoveModelConditions *)goalObject)->clearAndSetModelConditionFlags(
				Rva00170C70BitSet(0, 0x42), BfmeI1166(0, 0x43, 0x44));
		}
		return STATE_SUCCESS;
	}
	if (ai != 0 && ai->isIdle())
		return STATE_FAILURE;
	return STATE_CONTINUE;
}
