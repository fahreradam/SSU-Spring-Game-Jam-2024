#pragma once
#include "TrashType.generated.h"

USTRUCT(BlueprintType)
struct FTrashType : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Mesh;
};
