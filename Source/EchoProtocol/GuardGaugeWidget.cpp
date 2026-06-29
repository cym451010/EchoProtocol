// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardGaugeWidget.h"
#include "Components/ProgressBar.h"

void UGuardGaugeWidget::SetSightGauge(float Value)
{
	if (!SightProgressBar)
	{
		return;
	}

	SightProgressBar->SetPercent(Value);
}
